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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uiOpenTypeFeatures ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 size_t curFeature ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** features ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t nFeatures ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * uiNewOpenTypeFeatures () ; 
 int /*<<< orphan*/  uiOpenTypeFeaturesAdd (int /*<<< orphan*/ *,char const,char const,char const,char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uiOpenTypeFeatures *addFeature(const char tag[4], uint32_t value)
{
	uiOpenTypeFeatures *otf;

	if (curFeature >= nFeatures) {
		fprintf(stderr, "TODO (also TODO is there a panic function?)\n");
		exit(EXIT_FAILURE);
	}
	otf = uiNewOpenTypeFeatures();
	uiOpenTypeFeaturesAdd(otf, tag[0], tag[1], tag[2], tag[3], value);
	features[curFeature] = otf;
	curFeature++;
	return otf;
}