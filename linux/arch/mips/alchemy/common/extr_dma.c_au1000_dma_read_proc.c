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
struct dma_chan {char* dev_str; } ;
typedef  int off_t ;

/* Variables and functions */
 int NUM_AU1000_DMA_CHANNELS ; 
 struct dma_chan* get_dma_chan (int) ; 
 scalar_t__ sprintf (char*,char*,int,char*) ; 

int au1000_dma_read_proc(char *buf, char **start, off_t fpos,
			 int length, int *eof, void *data)
{
	int i, len = 0;
	struct dma_chan *chan;

	for (i = 0; i < NUM_AU1000_DMA_CHANNELS; i++) {
		chan = get_dma_chan(i);
		if (chan != NULL)
			len += sprintf(buf + len, "%2d: %s\n",
				       i, chan->dev_str);
	}

	if (fpos >= len) {
		*start = buf;
		*eof = 1;
		return 0;
	}
	*start = buf + fpos;
	len -= fpos;
	if (len > length)
		return length;
	*eof = 1;
	return len;
}