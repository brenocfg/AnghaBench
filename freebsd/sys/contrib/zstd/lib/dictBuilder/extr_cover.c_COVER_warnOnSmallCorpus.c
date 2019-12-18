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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  LOCALDISPLAYLEVEL (int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double const) ; 

void COVER_warnOnSmallCorpus(size_t maxDictSize, size_t nbDmers, int displayLevel)
{
  const double ratio = (double)nbDmers / maxDictSize;
  if (ratio >= 10) {
      return;
  }
  LOCALDISPLAYLEVEL(displayLevel, 1,
                    "WARNING: The maximum dictionary size %u is too large "
                    "compared to the source size %u! "
                    "size(source)/size(dictionary) = %f, but it should be >= "
                    "10! This may lead to a subpar dictionary! We recommend "
                    "training on sources at least 10x, and preferably 100x "
                    "the size of the dictionary! \n", (U32)maxDictSize,
                    (U32)nbDmers, ratio);
}