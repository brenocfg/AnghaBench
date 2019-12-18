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
struct sata_gemini {int muxmode; } ;
typedef  enum gemini_muxmode { ____Placeholder_gemini_muxmode } gemini_muxmode ;

/* Variables and functions */

enum gemini_muxmode gemini_sata_get_muxmode(struct sata_gemini *sg)
{
	return sg->muxmode;
}