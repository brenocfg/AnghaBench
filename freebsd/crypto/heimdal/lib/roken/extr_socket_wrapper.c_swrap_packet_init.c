#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_11__ {unsigned short source_port; unsigned short dest_port; void* checksum; void* length; } ;
struct TYPE_10__ {unsigned short source_port; unsigned short dest_port; int hdr_length; unsigned char control; void* urg; void* checksum; void* window; void* ack_num; void* seq_num; } ;
struct TYPE_9__ {int type; int code; void* unused; void* checksum; } ;
struct TYPE_12__ {TYPE_3__ udp; TYPE_2__ tcp; TYPE_1__ icmp; } ;
struct TYPE_15__ {int ver_hdrlen; int tos; int flags; int ttl; unsigned char protocol; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  src_addr; void* hdr_checksum; void* fragment; void* identification; void* packet_length; } ;
struct TYPE_16__ {TYPE_4__ p; TYPE_7__ hdr; } ;
struct TYPE_13__ {size_t recorded_length; size_t full_length; int /*<<< orphan*/  micro_seconds; int /*<<< orphan*/  seconds; } ;
struct swrap_packet {TYPE_8__ ip; TYPE_5__ frame; } ;
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {unsigned short sin_port; TYPE_6__ sin_addr; } ;

/* Variables and functions */
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 void* htonl (unsigned long) ; 
 void* htons (int) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 

__attribute__((used)) static struct swrap_packet *swrap_packet_init(struct timeval *tval,
					      const struct sockaddr_in *src_addr,
					      const struct sockaddr_in *dest_addr,
					      int socket_type,
					      const unsigned char *payload,
					      size_t payload_len,
					      unsigned long tcp_seq,
					      unsigned long tcp_ack,
					      unsigned char tcp_ctl,
					      int unreachable,
					      size_t *_packet_len)
{
	struct swrap_packet *ret;
	struct swrap_packet *packet;
	size_t packet_len;
	size_t alloc_len;
	size_t nonwire_len = sizeof(packet->frame);
	size_t wire_hdr_len = 0;
	size_t wire_len = 0;
	size_t icmp_hdr_len = 0;
	size_t icmp_truncate_len = 0;
	unsigned char protocol = 0, icmp_protocol = 0;
	unsigned short src_port = src_addr->sin_port;
	unsigned short dest_port = dest_addr->sin_port;

	switch (socket_type) {
	case SOCK_STREAM:
		protocol = 0x06; /* TCP */
		wire_hdr_len = sizeof(packet->ip.hdr) + sizeof(packet->ip.p.tcp);
		wire_len = wire_hdr_len + payload_len;
		break;

	case SOCK_DGRAM:
		protocol = 0x11; /* UDP */
		wire_hdr_len = sizeof(packet->ip.hdr) + sizeof(packet->ip.p.udp);
		wire_len = wire_hdr_len + payload_len;
		break;
	}

	if (unreachable) {
		icmp_protocol = protocol;
		protocol = 0x01; /* ICMP */
		if (wire_len > 64 ) {
			icmp_truncate_len = wire_len - 64;
		}
		icmp_hdr_len = sizeof(packet->ip.hdr) + sizeof(packet->ip.p.icmp);
		wire_hdr_len += icmp_hdr_len;
		wire_len += icmp_hdr_len;
	}

	packet_len = nonwire_len + wire_len;
	alloc_len = packet_len;
	if (alloc_len < sizeof(struct swrap_packet)) {
		alloc_len = sizeof(struct swrap_packet);
	}
	ret = (struct swrap_packet *)malloc(alloc_len);
	if (!ret) return NULL;

	packet = ret;

	packet->frame.seconds		= tval->tv_sec;
	packet->frame.micro_seconds	= tval->tv_usec;
	packet->frame.recorded_length	= wire_len - icmp_truncate_len;
	packet->frame.full_length	= wire_len - icmp_truncate_len;

	packet->ip.hdr.ver_hdrlen	= 0x45; /* version 4 and 5 * 32 bit words */
	packet->ip.hdr.tos		= 0x00;
	packet->ip.hdr.packet_length	= htons(wire_len - icmp_truncate_len);
	packet->ip.hdr.identification	= htons(0xFFFF);
	packet->ip.hdr.flags		= 0x40; /* BIT 1 set - means don't fraqment */
	packet->ip.hdr.fragment		= htons(0x0000);
	packet->ip.hdr.ttl		= 0xFF;
	packet->ip.hdr.protocol		= protocol;
	packet->ip.hdr.hdr_checksum	= htons(0x0000);
	packet->ip.hdr.src_addr		= src_addr->sin_addr.s_addr;
	packet->ip.hdr.dest_addr	= dest_addr->sin_addr.s_addr;

	if (unreachable) {
		packet->ip.p.icmp.type		= 0x03; /* destination unreachable */
		packet->ip.p.icmp.code		= 0x01; /* host unreachable */
		packet->ip.p.icmp.checksum	= htons(0x0000);
		packet->ip.p.icmp.unused	= htonl(0x00000000);

		/* set the ip header in the ICMP payload */
		packet = (struct swrap_packet *)(((unsigned char *)ret) + icmp_hdr_len);
		packet->ip.hdr.ver_hdrlen	= 0x45; /* version 4 and 5 * 32 bit words */
		packet->ip.hdr.tos		= 0x00;
		packet->ip.hdr.packet_length	= htons(wire_len - icmp_hdr_len);
		packet->ip.hdr.identification	= htons(0xFFFF);
		packet->ip.hdr.flags		= 0x40; /* BIT 1 set - means don't fraqment */
		packet->ip.hdr.fragment		= htons(0x0000);
		packet->ip.hdr.ttl		= 0xFF;
		packet->ip.hdr.protocol		= icmp_protocol;
		packet->ip.hdr.hdr_checksum	= htons(0x0000);
		packet->ip.hdr.src_addr		= dest_addr->sin_addr.s_addr;
		packet->ip.hdr.dest_addr	= src_addr->sin_addr.s_addr;

		src_port = dest_addr->sin_port;
		dest_port = src_addr->sin_port;
	}

	switch (socket_type) {
	case SOCK_STREAM:
		packet->ip.p.tcp.source_port	= src_port;
		packet->ip.p.tcp.dest_port	= dest_port;
		packet->ip.p.tcp.seq_num	= htonl(tcp_seq);
		packet->ip.p.tcp.ack_num	= htonl(tcp_ack);
		packet->ip.p.tcp.hdr_length	= 0x50; /* 5 * 32 bit words */
		packet->ip.p.tcp.control	= tcp_ctl;
		packet->ip.p.tcp.window		= htons(0x7FFF);
		packet->ip.p.tcp.checksum	= htons(0x0000);
		packet->ip.p.tcp.urg		= htons(0x0000);

		break;

	case SOCK_DGRAM:
		packet->ip.p.udp.source_port	= src_addr->sin_port;
		packet->ip.p.udp.dest_port	= dest_addr->sin_port;
		packet->ip.p.udp.length		= htons(8 + payload_len);
		packet->ip.p.udp.checksum	= htons(0x0000);

		break;
	}

	if (payload && payload_len > 0) {
		unsigned char *p = (unsigned char *)ret;
		p += nonwire_len;
		p += wire_hdr_len;
		memcpy(p, payload, payload_len);
	}

	*_packet_len = packet_len - icmp_truncate_len;
	return ret;
}