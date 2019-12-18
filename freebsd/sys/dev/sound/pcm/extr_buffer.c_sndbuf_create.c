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
struct snd_dbuf {struct pcm_channel* channel; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct pcm_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SNDBUF_NAMELEN ; 
 struct snd_dbuf* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 

struct snd_dbuf *
sndbuf_create(device_t dev, char *drv, char *desc, struct pcm_channel *channel)
{
	struct snd_dbuf *b;

	b = malloc(sizeof(*b), M_DEVBUF, M_WAITOK | M_ZERO);
	snprintf(b->name, SNDBUF_NAMELEN, "%s:%s", drv, desc);
	b->dev = dev;
	b->channel = channel;

	return b;
}