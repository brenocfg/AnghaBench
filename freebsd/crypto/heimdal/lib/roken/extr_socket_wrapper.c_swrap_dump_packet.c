#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct swrap_packet {int dummy; } ;
struct TYPE_2__ {unsigned long pck_snd; unsigned long pck_rcv; } ;
struct socket_info {int family; int /*<<< orphan*/  type; TYPE_1__ io; struct sockaddr* peername; scalar_t__ myname; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  enum swrap_packet_type { ____Placeholder_swrap_packet_type } swrap_packet_type ;

/* Variables and functions */
#define  AF_INET 147 
#define  AF_INET6 146 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
#define  SWRAP_ACCEPT_ACK 145 
#define  SWRAP_ACCEPT_RECV 144 
#define  SWRAP_ACCEPT_SEND 143 
#define  SWRAP_CLOSE_ACK 142 
#define  SWRAP_CLOSE_RECV 141 
#define  SWRAP_CLOSE_SEND 140 
#define  SWRAP_CONNECT_ACK 139 
#define  SWRAP_CONNECT_RECV 138 
#define  SWRAP_CONNECT_SEND 137 
#define  SWRAP_CONNECT_UNREACH 136 
#define  SWRAP_PENDING_RST 135 
#define  SWRAP_RECV 134 
#define  SWRAP_RECVFROM 133 
#define  SWRAP_RECV_RST 132 
#define  SWRAP_SEND 131 
#define  SWRAP_SENDTO 130 
#define  SWRAP_SENDTO_UNREACH 129 
#define  SWRAP_SEND_RST 128 
 int /*<<< orphan*/  free (struct swrap_packet*) ; 
 char* socket_wrapper_pcap_file () ; 
 int /*<<< orphan*/  swrapGetTimeOfDay (struct timeval*) ; 
 int swrap_get_pcap_fd (char const*) ; 
 struct swrap_packet* swrap_packet_init (struct timeval*,struct sockaddr_in const*,struct sockaddr_in const*,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned long,unsigned long,unsigned char,int,size_t*) ; 
 int /*<<< orphan*/  write (int,struct swrap_packet*,size_t) ; 

__attribute__((used)) static void swrap_dump_packet(struct socket_info *si, const struct sockaddr *addr,
			      enum swrap_packet_type type,
			      const void *buf, size_t len)
{
	const struct sockaddr_in *src_addr;
	const struct sockaddr_in *dest_addr;
	const char *file_name;
	unsigned long tcp_seq = 0;
	unsigned long tcp_ack = 0;
	unsigned char tcp_ctl = 0;
	int unreachable = 0;
	struct timeval tv;
	struct swrap_packet *packet;
	size_t packet_len = 0;
	int fd;

	file_name = socket_wrapper_pcap_file();
	if (!file_name) {
		return;
	}

	switch (si->family) {
	case AF_INET:
#ifdef HAVE_IPV6
	case AF_INET6:
#endif
		break;
	default:
		return;
	}

	switch (type) {
	case SWRAP_CONNECT_SEND:
		if (si->type != SOCK_STREAM) return;

		src_addr = (const struct sockaddr_in *)si->myname;
		dest_addr = (const struct sockaddr_in *)addr;

		tcp_seq = si->io.pck_snd;
		tcp_ack = si->io.pck_rcv;
		tcp_ctl = 0x02; /* SYN */

		si->io.pck_snd += 1;

		break;

	case SWRAP_CONNECT_RECV:
		if (si->type != SOCK_STREAM) return;

		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)addr;

		tcp_seq = si->io.pck_rcv;
		tcp_ack = si->io.pck_snd;
		tcp_ctl = 0x12; /** SYN,ACK */

		si->io.pck_rcv += 1;

		break;

	case SWRAP_CONNECT_UNREACH:
		if (si->type != SOCK_STREAM) return;

		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)addr;

		/* Unreachable: resend the data of SWRAP_CONNECT_SEND */
		tcp_seq = si->io.pck_snd - 1;
		tcp_ack = si->io.pck_rcv;
		tcp_ctl = 0x02; /* SYN */
		unreachable = 1;

		break;

	case SWRAP_CONNECT_ACK:
		if (si->type != SOCK_STREAM) return;

		src_addr = (const struct sockaddr_in *)si->myname;
		dest_addr = (const struct sockaddr_in *)addr;

		tcp_seq = si->io.pck_snd;
		tcp_ack = si->io.pck_rcv;
		tcp_ctl = 0x10; /* ACK */

		break;

	case SWRAP_ACCEPT_SEND:
		if (si->type != SOCK_STREAM) return;

		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)addr;

		tcp_seq = si->io.pck_rcv;
		tcp_ack = si->io.pck_snd;
		tcp_ctl = 0x02; /* SYN */

		si->io.pck_rcv += 1;

		break;

	case SWRAP_ACCEPT_RECV:
		if (si->type != SOCK_STREAM) return;

		src_addr = (const struct sockaddr_in *)si->myname;
		dest_addr = (const struct sockaddr_in *)addr;

		tcp_seq = si->io.pck_snd;
		tcp_ack = si->io.pck_rcv;
		tcp_ctl = 0x12; /* SYN,ACK */

		si->io.pck_snd += 1;

		break;

	case SWRAP_ACCEPT_ACK:
		if (si->type != SOCK_STREAM) return;

		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)addr;

		tcp_seq = si->io.pck_rcv;
		tcp_ack = si->io.pck_snd;
		tcp_ctl = 0x10; /* ACK */

		break;

	case SWRAP_SEND:
		src_addr = (const struct sockaddr_in *)si->myname;
		dest_addr = (const struct sockaddr_in *)si->peername;

		tcp_seq = si->io.pck_snd;
		tcp_ack = si->io.pck_rcv;
		tcp_ctl = 0x18; /* PSH,ACK */

		si->io.pck_snd += len;

		break;

	case SWRAP_SEND_RST:
		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)si->peername;

		if (si->type == SOCK_DGRAM) {
			swrap_dump_packet(si, si->peername,
					  SWRAP_SENDTO_UNREACH,
			      		  buf, len);
			return;
		}

		tcp_seq = si->io.pck_rcv;
		tcp_ack = si->io.pck_snd;
		tcp_ctl = 0x14; /** RST,ACK */

		break;

	case SWRAP_PENDING_RST:
		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)si->peername;

		if (si->type == SOCK_DGRAM) {
			return;
		}

		tcp_seq = si->io.pck_rcv;
		tcp_ack = si->io.pck_snd;
		tcp_ctl = 0x14; /* RST,ACK */

		break;

	case SWRAP_RECV:
		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)si->peername;

		tcp_seq = si->io.pck_rcv;
		tcp_ack = si->io.pck_snd;
		tcp_ctl = 0x18; /* PSH,ACK */

		si->io.pck_rcv += len;

		break;

	case SWRAP_RECV_RST:
		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)si->peername;

		if (si->type == SOCK_DGRAM) {
			return;
		}

		tcp_seq = si->io.pck_rcv;
		tcp_ack = si->io.pck_snd;
		tcp_ctl = 0x14; /* RST,ACK */

		break;

	case SWRAP_SENDTO:
		src_addr = (const struct sockaddr_in *)si->myname;
		dest_addr = (const struct sockaddr_in *)addr;

		si->io.pck_snd += len;

		break;

	case SWRAP_SENDTO_UNREACH:
		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)addr;

		unreachable = 1;

		break;

	case SWRAP_RECVFROM:
		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)addr;

		si->io.pck_rcv += len;

		break;

	case SWRAP_CLOSE_SEND:
		if (si->type != SOCK_STREAM) return;

		src_addr = (const struct sockaddr_in *)si->myname;
		dest_addr = (const struct sockaddr_in *)si->peername;

		tcp_seq = si->io.pck_snd;
		tcp_ack = si->io.pck_rcv;
		tcp_ctl = 0x11; /* FIN, ACK */

		si->io.pck_snd += 1;

		break;

	case SWRAP_CLOSE_RECV:
		if (si->type != SOCK_STREAM) return;

		dest_addr = (const struct sockaddr_in *)si->myname;
		src_addr = (const struct sockaddr_in *)si->peername;

		tcp_seq = si->io.pck_rcv;
		tcp_ack = si->io.pck_snd;
		tcp_ctl = 0x11; /* FIN,ACK */

		si->io.pck_rcv += 1;

		break;

	case SWRAP_CLOSE_ACK:
		if (si->type != SOCK_STREAM) return;

		src_addr = (const struct sockaddr_in *)si->myname;
		dest_addr = (const struct sockaddr_in *)si->peername;

		tcp_seq = si->io.pck_snd;
		tcp_ack = si->io.pck_rcv;
		tcp_ctl = 0x10; /* ACK */

		break;
	default:
		return;
	}

	swrapGetTimeOfDay(&tv);

	packet = swrap_packet_init(&tv, src_addr, dest_addr, si->type,
				   (const unsigned char *)buf, len,
				   tcp_seq, tcp_ack, tcp_ctl, unreachable,
				   &packet_len);
	if (!packet) {
		return;
	}

	fd = swrap_get_pcap_fd(file_name);
	if (fd != -1) {
		write(fd, packet, packet_len);
	}

	free(packet);
}