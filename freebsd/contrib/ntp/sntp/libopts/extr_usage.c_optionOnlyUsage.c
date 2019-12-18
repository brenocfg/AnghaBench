#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_1__ tOptions ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 scalar_t__ do_gnu_usage (TYPE_1__*) ; 
 scalar_t__ ferror (scalar_t__) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fserr_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ option_usage_fp ; 
 int /*<<< orphan*/  prt_opt_usage (TYPE_1__*,int,char const*) ; 
 int /*<<< orphan*/  setGnuOptFmts (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  setStdOptFmts (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  set_usage_flags (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ skip_misuse_usage (TYPE_1__*) ; 
 scalar_t__ stderr ; 
 int /*<<< orphan*/  zstderr_name ; 
 int /*<<< orphan*/  zstdout_name ; 
 int /*<<< orphan*/  zwriting ; 

void
optionOnlyUsage(tOptions * pOpts, int ex_code)
{
    char const * pOptTitle = NULL;

    set_usage_flags(pOpts, NULL);
    if ((ex_code != EXIT_SUCCESS) &&
        skip_misuse_usage(pOpts))
        return;

    /*
     *  Determine which header and which option formatting strings to use
     */
    if (do_gnu_usage(pOpts))
        (void)setGnuOptFmts(pOpts, &pOptTitle);
    else
        (void)setStdOptFmts(pOpts, &pOptTitle);

    prt_opt_usage(pOpts, ex_code, pOptTitle);

    fflush(option_usage_fp);
    if (ferror(option_usage_fp) != 0)
        fserr_exit(pOpts->pzProgName, zwriting, (option_usage_fp == stderr)
                   ? zstderr_name : zstdout_name);
}