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
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  BMK_benchOutcome_t ;
typedef  int /*<<< orphan*/  BMK_advancedParams_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_benchFilesAdvanced (char const* const*,unsigned int,char const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BMK_initAdvancedParams () ; 

BMK_benchOutcome_t BMK_benchFiles(
                    const char* const * fileNamesTable, unsigned nbFiles,
                    const char* dictFileName,
                    int cLevel, const ZSTD_compressionParameters* compressionParams,
                    int displayLevel)
{
    BMK_advancedParams_t const adv = BMK_initAdvancedParams();
    return BMK_benchFilesAdvanced(fileNamesTable, nbFiles, dictFileName, cLevel, compressionParams, displayLevel, &adv);
}