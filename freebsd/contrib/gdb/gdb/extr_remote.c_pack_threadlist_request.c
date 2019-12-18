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
typedef  int /*<<< orphan*/  threadref ;

/* Variables and functions */
 char* pack_hex_byte (char*,int) ; 
 char* pack_nibble (char*,int) ; 
 char* pack_threadid (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
pack_threadlist_request (char *pkt, int startflag, int threadcount,
			 threadref *nextthread)
{
  *pkt++ = 'q';			/* info query packet */
  *pkt++ = 'L';			/* Process LIST or threadLIST request */
  pkt = pack_nibble (pkt, startflag);	/* initflag 1 bytes */
  pkt = pack_hex_byte (pkt, threadcount);	/* threadcount 2 bytes */
  pkt = pack_threadid (pkt, nextthread);	/* 64 bit thread identifier */
  *pkt = '\0';
  return pkt;
}