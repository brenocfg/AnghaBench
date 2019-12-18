#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct listen_port {int dummy; } ;
struct config_strlist {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int if_is_ssl (char const*,char const*,int,struct config_strlist*) ; 
 int /*<<< orphan*/  listen_type_ssl ; 
 int /*<<< orphan*/  listen_type_tcp ; 
 int /*<<< orphan*/  listen_type_tcp_dnscrypt ; 
 int /*<<< orphan*/  listen_type_udp ; 
 int /*<<< orphan*/  listen_type_udp_dnscrypt ; 
 int /*<<< orphan*/  listen_type_udpancil ; 
 int /*<<< orphan*/  listen_type_udpancil_dnscrypt ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int make_sock_port (int /*<<< orphan*/ ,char const*,char const*,struct addrinfo*,int,int*,size_t,size_t,int*,int,int,int,int) ; 
 int /*<<< orphan*/  port_insert (struct listen_port**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_recvpktinfo (int,int /*<<< orphan*/ ) ; 
 char const* strchr (char const*,char) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ports_create_if(const char* ifname, int do_auto, int do_udp, int do_tcp, 
	struct addrinfo *hints, const char* port, struct listen_port** list,
	size_t rcv, size_t snd, int ssl_port,
	struct config_strlist* tls_additional_port, int* reuseport,
	int transparent, int tcp_mss, int freebind, int use_systemd,
	int dnscrypt_port)
{
	int s, noip6=0;
#ifdef USE_DNSCRYPT
	int is_dnscrypt = ((strchr(ifname, '@') && 
			atoi(strchr(ifname, '@')+1) == dnscrypt_port) ||
			(!strchr(ifname, '@') && atoi(port) == dnscrypt_port));
#else
	int is_dnscrypt = 0;
	(void)dnscrypt_port;
#endif

	if(!do_udp && !do_tcp)
		return 0;
	if(do_auto) {
		if((s = make_sock_port(SOCK_DGRAM, ifname, port, hints, 1, 
			&noip6, rcv, snd, reuseport, transparent,
			tcp_mss, freebind, use_systemd)) == -1) {
			if(noip6) {
				log_warn("IPv6 protocol not available");
				return 1;
			}
			return 0;
		}
		/* getting source addr packet info is highly non-portable */
		if(!set_recvpktinfo(s, hints->ai_family)) {
#ifndef USE_WINSOCK
			close(s);
#else
			closesocket(s);
#endif
			return 0;
		}
		if(!port_insert(list, s,
		   is_dnscrypt?listen_type_udpancil_dnscrypt:listen_type_udpancil)) {
#ifndef USE_WINSOCK
			close(s);
#else
			closesocket(s);
#endif
			return 0;
		}
	} else if(do_udp) {
		/* regular udp socket */
		if((s = make_sock_port(SOCK_DGRAM, ifname, port, hints, 1, 
			&noip6, rcv, snd, reuseport, transparent,
			tcp_mss, freebind, use_systemd)) == -1) {
			if(noip6) {
				log_warn("IPv6 protocol not available");
				return 1;
			}
			return 0;
		}
		if(!port_insert(list, s,
		   is_dnscrypt?listen_type_udp_dnscrypt:listen_type_udp)) {
#ifndef USE_WINSOCK
			close(s);
#else
			closesocket(s);
#endif
			return 0;
		}
	}
	if(do_tcp) {
		int is_ssl = if_is_ssl(ifname, port, ssl_port,
			tls_additional_port);
		if((s = make_sock_port(SOCK_STREAM, ifname, port, hints, 1, 
			&noip6, 0, 0, reuseport, transparent, tcp_mss,
			freebind, use_systemd)) == -1) {
			if(noip6) {
				/*log_warn("IPv6 protocol not available");*/
				return 1;
			}
			return 0;
		}
		if(is_ssl)
			verbose(VERB_ALGO, "setup TCP for SSL service");
		if(!port_insert(list, s, is_ssl?listen_type_ssl:
			(is_dnscrypt?listen_type_tcp_dnscrypt:listen_type_tcp))) {
#ifndef USE_WINSOCK
			close(s);
#else
			closesocket(s);
#endif
			return 0;
		}
	}
	return 1;
}