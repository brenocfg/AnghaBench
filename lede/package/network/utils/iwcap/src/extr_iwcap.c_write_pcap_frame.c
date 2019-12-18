#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct timeval {void* tv_usec; void* tv_sec; } ;
struct TYPE_3__ {void* orig_len; void* incl_len; void* ts_usec; void* ts_sec; } ;
typedef  TYPE_1__ pcaprec_hdr_t ;
typedef  int /*<<< orphan*/  fhdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

void write_pcap_frame(FILE *o, uint32_t *sec, uint32_t *usec,
					  uint16_t len, uint16_t olen)
{
	struct timeval tv;
	pcaprec_hdr_t fhdr;

	if (!sec || !usec)
	{
		gettimeofday(&tv, NULL);
	}
	else
	{
		tv.tv_sec  = *sec;
		tv.tv_usec = *usec;
	}

	fhdr.ts_sec   = tv.tv_sec;
	fhdr.ts_usec  = tv.tv_usec;
	fhdr.incl_len = len;
	fhdr.orig_len = olen;

	fwrite(&fhdr, 1, sizeof(fhdr), o);
}