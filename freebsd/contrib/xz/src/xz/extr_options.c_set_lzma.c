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
typedef  void* uint64_t ;
typedef  char uint32_t ;
struct TYPE_2__ {void* depth; void* mf; void* nice_len; void* mode; void* pb; void* lp; void* lc; void* dict_size; } ;
typedef  TYPE_1__ lzma_options_lzma ;

/* Variables and functions */
 char LZMA_PRESET_EXTREME ; 
#define  OPT_DEPTH 136 
#define  OPT_DICT 135 
#define  OPT_LC 134 
#define  OPT_LP 133 
#define  OPT_MF 132 
#define  OPT_MODE 131 
#define  OPT_NICE 130 
#define  OPT_PB 129 
#define  OPT_PRESET 128 
 int /*<<< orphan*/  error_lzma_preset (char const*) ; 
 int /*<<< orphan*/  lzma_lzma_preset (void*,char) ; 

__attribute__((used)) static void
set_lzma(void *options, unsigned key, uint64_t value, const char *valuestr)
{
	lzma_options_lzma *opt = options;

	switch (key) {
	case OPT_PRESET: {
		if (valuestr[0] < '0' || valuestr[0] > '9')
			error_lzma_preset(valuestr);

		uint32_t preset = valuestr[0] - '0';

		// Currently only "e" is supported as a modifier,
		// so keep this simple for now.
		if (valuestr[1] != '\0') {
			if (valuestr[1] == 'e')
				preset |= LZMA_PRESET_EXTREME;
			else
				error_lzma_preset(valuestr);

			if (valuestr[2] != '\0')
				error_lzma_preset(valuestr);
		}

		if (lzma_lzma_preset(options, preset))
			error_lzma_preset(valuestr);

		break;
	}

	case OPT_DICT:
		opt->dict_size = value;
		break;

	case OPT_LC:
		opt->lc = value;
		break;

	case OPT_LP:
		opt->lp = value;
		break;

	case OPT_PB:
		opt->pb = value;
		break;

	case OPT_MODE:
		opt->mode = value;
		break;

	case OPT_NICE:
		opt->nice_len = value;
		break;

	case OPT_MF:
		opt->mf = value;
		break;

	case OPT_DEPTH:
		opt->depth = value;
		break;
	}
}