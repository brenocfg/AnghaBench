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
struct mkuz_lzma {TYPE_1__* filters; int /*<<< orphan*/  opt_lzma; scalar_t__ strm; } ;
typedef  scalar_t__ lzma_stream ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * options; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FILTER_LZMA2 ; 
 int LZMA_PRESET_DEFAULT ; 
 scalar_t__ LZMA_STREAM_INIT ; 
 int /*<<< orphan*/  LZMA_VLI_UNKNOWN ; 
 int USE_DEFAULT_LEVEL ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ lzma_lzma_preset (int /*<<< orphan*/ *,int) ; 
 struct mkuz_lzma* mkuz_safe_zmalloc (int) ; 

void *
mkuz_lzma_init(int *comp_level)
{
	struct mkuz_lzma *ulp;

	if (*comp_level == USE_DEFAULT_LEVEL)
		*comp_level = LZMA_PRESET_DEFAULT;
	if (*comp_level < 0 || *comp_level > 9)
		errx(1, "provided compression level %d is invalid",
		    *comp_level);
		/* Not reached */

	ulp = mkuz_safe_zmalloc(sizeof(struct mkuz_lzma));

	/* Init lzma encoder */
	ulp->strm = (lzma_stream)LZMA_STREAM_INIT;
	if (lzma_lzma_preset(&ulp->opt_lzma, *comp_level))
		errx(1, "Error loading LZMA preset");

	ulp->filters[0].id = LZMA_FILTER_LZMA2;
	ulp->filters[0].options = &ulp->opt_lzma;
	ulp->filters[1].id = LZMA_VLI_UNKNOWN;

	return (void *)ulp;
}