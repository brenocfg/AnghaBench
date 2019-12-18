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
struct TYPE_2__ {unsigned int hclk_tns; } ;
struct s3c_cpufreq_config {TYPE_1__ freq; } ;
struct s3c2412_iobank_timing {int /*<<< orphan*/  wstbrd; void* smbwstbrd; int /*<<< orphan*/  wstwen; void* smbwstwen; int /*<<< orphan*/  wstoen; void* smbwstoen; int /*<<< orphan*/  wstwr; void* smbwstwr; int /*<<< orphan*/  wstrd; void* smbwstrd; int /*<<< orphan*/  idcy; void* smbidcyr; } ;

/* Variables and functions */
 void* calc_timing (int /*<<< orphan*/ ,unsigned int,int*) ; 

__attribute__((used)) static int s3c2412_calc_bank(struct s3c_cpufreq_config *cfg,
			     struct s3c2412_iobank_timing *bt)
{
	unsigned int hclk = cfg->freq.hclk_tns;
	int err = 0;

	bt->smbidcyr = calc_timing(bt->idcy, hclk, &err);
	bt->smbwstrd = calc_timing(bt->wstrd, hclk, &err);
	bt->smbwstwr = calc_timing(bt->wstwr, hclk, &err);
	bt->smbwstoen = calc_timing(bt->wstoen, hclk, &err);
	bt->smbwstwen = calc_timing(bt->wstwen, hclk, &err);
	bt->smbwstbrd = calc_timing(bt->wstbrd, hclk, &err);

	return err;
}