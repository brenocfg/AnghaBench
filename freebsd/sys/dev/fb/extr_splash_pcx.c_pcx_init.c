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
typedef  int uint8_t ;
struct pcx_header {int manufactor; int version; int encoding; int nplanes; int bpp; scalar_t__ bpsl; scalar_t__ ymin; scalar_t__ ymax; scalar_t__ xmin; scalar_t__ xmax; } ;
struct TYPE_2__ {scalar_t__ bpsl; int bpp; int planes; int zlen; int* zdata; int* palette; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 scalar_t__ MAXSCANLINE ; 
 TYPE_1__ pcx_info ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
pcx_init(void *data, int size)
{
	const struct pcx_header *hdr = data;

	if (size < 128 + 1 + 1 + 768 ||
	    hdr->manufactor != 10 ||
	    hdr->version != 5 ||
	    hdr->encoding != 1 ||
	    hdr->nplanes != 1 ||
	    hdr->bpp != 8 ||
	    hdr->bpsl > MAXSCANLINE ||
	    ((uint8_t *)data)[size - 769] != 12) {
		printf("splash_pcx: invalid PCX image\n");
		return (1);
	}
	pcx_info.width = hdr->xmax - hdr->xmin + 1;
	pcx_info.height = hdr->ymax - hdr->ymin + 1;
	pcx_info.bpsl = hdr->bpsl;
	pcx_info.bpp = hdr->bpp;
	pcx_info.planes = hdr->nplanes;
	pcx_info.zlen = size - (128 + 1 + 768);
	pcx_info.zdata = (uint8_t *)data + 128;
	pcx_info.palette = (uint8_t *)data + size - 768;
	return (0);
}