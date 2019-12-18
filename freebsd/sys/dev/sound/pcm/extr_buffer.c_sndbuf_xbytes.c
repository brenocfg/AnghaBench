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
struct snd_dbuf {int dummy; } ;

/* Variables and functions */
 unsigned int snd_xbytes (unsigned int,int,int) ; 
 int sndbuf_getalign (struct snd_dbuf*) ; 
 int sndbuf_getspd (struct snd_dbuf*) ; 

unsigned int
sndbuf_xbytes(unsigned int v, struct snd_dbuf *from, struct snd_dbuf *to)
{
	if (from == NULL || to == NULL || v == 0)
		return 0;

	return snd_xbytes(v, sndbuf_getalign(from) * sndbuf_getspd(from),
	    sndbuf_getalign(to) * sndbuf_getspd(to));
}