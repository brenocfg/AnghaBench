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
typedef  void* uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct rpcap_header {int /*<<< orphan*/  plen; int /*<<< orphan*/  value; void* type; void* ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rpcap_header*,int /*<<< orphan*/ ,int) ; 

void
rpcap_createhdr(struct rpcap_header *header, uint8 ver, uint8 type, uint16 value, uint32 length)
{
	memset(header, 0, sizeof(struct rpcap_header));

	header->ver = ver;
	header->type = type;
	header->value = htons(value);
	header->plen = htonl(length);
}