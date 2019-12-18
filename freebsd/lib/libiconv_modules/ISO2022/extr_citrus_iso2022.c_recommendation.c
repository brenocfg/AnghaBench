#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t* recommendsize; scalar_t__ maxcharset; TYPE_2__** recommend; } ;
typedef  TYPE_1__ _ISO2022EncodingInfo ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ final; scalar_t__ interm; } ;
typedef  TYPE_2__ _ISO2022Charset ;

/* Variables and functions */
#define  CS94 131 
#define  CS94MULTI 130 
#define  CS96 129 
#define  CS96MULTI 128 

__attribute__((used)) static int
recommendation(_ISO2022EncodingInfo * __restrict ei,
    _ISO2022Charset * __restrict cs)
{
	_ISO2022Charset *recommend;
	size_t j;
	int i;

	/* first, try a exact match. */
	for (i = 0; i < 4; i++) {
		recommend = ei->recommend[i];
		for (j = 0; j < ei->recommendsize[i]; j++) {
			if (cs->type != recommend[j].type)
				continue;
			if (cs->final != recommend[j].final)
				continue;
			if (cs->interm != recommend[j].interm)
				continue;

			return (i);
		}
	}

	/* then, try a wildcard match over final char. */
	for (i = 0; i < 4; i++) {
		recommend = ei->recommend[i];
		for (j = 0; j < ei->recommendsize[i]; j++) {
			if (cs->type != recommend[j].type)
				continue;
			if (cs->final && (cs->final != recommend[j].final))
				continue;
			if (cs->interm && (cs->interm != recommend[j].interm))
				continue;

			return (i);
		}
	}

	/* there's no recommendation. make a guess. */
	if (ei->maxcharset == 0) {
		return (0);
	} else {
		switch (cs->type) {
		case CS94:
		case CS94MULTI:
			return (0);
		case CS96:
		case CS96MULTI:
			return (1);
		}
	}
	return (0);
}