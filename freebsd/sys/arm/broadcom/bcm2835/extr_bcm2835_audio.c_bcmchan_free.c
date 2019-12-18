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
struct bcm2835_audio_chinfo {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* sndbuf_getbuf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcmchan_free(kobj_t obj, void *data)
{
	struct bcm2835_audio_chinfo *ch = data;
	void *buffer;

	buffer = sndbuf_getbuf(ch->buffer);
	if (buffer)
		free(buffer, M_DEVBUF);

	return (0);
}