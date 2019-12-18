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
struct config_file {int port; int do_ip4; int do_ip6; int do_tcp; scalar_t__ incoming_num_tcp; int num_ifs; char** ifs; int /*<<< orphan*/  dnscrypt_port; int /*<<< orphan*/  use_systemd; int /*<<< orphan*/  ip_freebind; int /*<<< orphan*/  tcp_mss; int /*<<< orphan*/  ip_transparent; int /*<<< orphan*/  tls_additional_port; int /*<<< orphan*/  ssl_port; int /*<<< orphan*/  so_sndbuf; int /*<<< orphan*/  so_rcvbuf; int /*<<< orphan*/  do_udp; scalar_t__ if_automatic; } ;
struct addrinfo {void* ai_family; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  portbuf ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 void* AF_UNSPEC ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  listening_ports_free (struct listen_port*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ports_create_if (char*,int,int /*<<< orphan*/ ,int,struct addrinfo*,char*,struct listen_port**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ str_is_ip6 (char*) ; 

struct listen_port* 
listening_ports_open(struct config_file* cfg, int* reuseport)
{
	struct listen_port* list = NULL;
	struct addrinfo hints;
	int i, do_ip4, do_ip6;
	int do_tcp, do_auto;
	char portbuf[32];
	snprintf(portbuf, sizeof(portbuf), "%d", cfg->port);
	do_ip4 = cfg->do_ip4;
	do_ip6 = cfg->do_ip6;
	do_tcp = cfg->do_tcp;
	do_auto = cfg->if_automatic && cfg->do_udp;
	if(cfg->incoming_num_tcp == 0)
		do_tcp = 0;

	/* getaddrinfo */
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	/* no name lookups on our listening ports */
	if(cfg->num_ifs > 0)
		hints.ai_flags |= AI_NUMERICHOST;
	hints.ai_family = AF_UNSPEC;
#ifndef INET6
	do_ip6 = 0;
#endif
	if(!do_ip4 && !do_ip6) {
		return NULL;
	}
	/* create ip4 and ip6 ports so that return addresses are nice. */
	if(do_auto || cfg->num_ifs == 0) {
		if(do_ip6) {
			hints.ai_family = AF_INET6;
			if(!ports_create_if(do_auto?"::0":"::1", 
				do_auto, cfg->do_udp, do_tcp, 
				&hints, portbuf, &list,
				cfg->so_rcvbuf, cfg->so_sndbuf,
				cfg->ssl_port, cfg->tls_additional_port,
				reuseport, cfg->ip_transparent,
				cfg->tcp_mss, cfg->ip_freebind, cfg->use_systemd,
				cfg->dnscrypt_port)) {
				listening_ports_free(list);
				return NULL;
			}
		}
		if(do_ip4) {
			hints.ai_family = AF_INET;
			if(!ports_create_if(do_auto?"0.0.0.0":"127.0.0.1", 
				do_auto, cfg->do_udp, do_tcp, 
				&hints, portbuf, &list,
				cfg->so_rcvbuf, cfg->so_sndbuf,
				cfg->ssl_port, cfg->tls_additional_port,
				reuseport, cfg->ip_transparent,
				cfg->tcp_mss, cfg->ip_freebind, cfg->use_systemd,
				cfg->dnscrypt_port)) {
				listening_ports_free(list);
				return NULL;
			}
		}
	} else for(i = 0; i<cfg->num_ifs; i++) {
		if(str_is_ip6(cfg->ifs[i])) {
			if(!do_ip6)
				continue;
			hints.ai_family = AF_INET6;
			if(!ports_create_if(cfg->ifs[i], 0, cfg->do_udp, 
				do_tcp, &hints, portbuf, &list, 
				cfg->so_rcvbuf, cfg->so_sndbuf,
				cfg->ssl_port, cfg->tls_additional_port,
				reuseport, cfg->ip_transparent,
				cfg->tcp_mss, cfg->ip_freebind, cfg->use_systemd,
				cfg->dnscrypt_port)) {
				listening_ports_free(list);
				return NULL;
			}
		} else {
			if(!do_ip4)
				continue;
			hints.ai_family = AF_INET;
			if(!ports_create_if(cfg->ifs[i], 0, cfg->do_udp, 
				do_tcp, &hints, portbuf, &list, 
				cfg->so_rcvbuf, cfg->so_sndbuf,
				cfg->ssl_port, cfg->tls_additional_port,
				reuseport, cfg->ip_transparent,
				cfg->tcp_mss, cfg->ip_freebind, cfg->use_systemd,
				cfg->dnscrypt_port)) {
				listening_ports_free(list);
				return NULL;
			}
		}
	}
	return list;
}