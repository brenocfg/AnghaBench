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
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_benchCLevel (void* const,size_t,char*,int,int,size_t*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 int /*<<< orphan*/  RDG_genBuffer (void* const,size_t,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void BMK_syntheticTest(int cLevel, int cLevelLast, double compressibility)
{
    char name[20] = {0};
    size_t benchedSize = 10000000;
    void* const srcBuffer = malloc(benchedSize);

    /* Memory allocation */
    if (!srcBuffer) EXM_THROW(21, "not enough memory");

    /* Fill input buffer */
    RDG_genBuffer(srcBuffer, benchedSize, compressibility, 0.0, 0);

    /* Bench */
    snprintf (name, sizeof(name), "Synthetic %2u%%", (unsigned)(compressibility*100));
    BMK_benchCLevel(srcBuffer, benchedSize, name, cLevel, cLevelLast, &benchedSize, 1, NULL, 0);

    /* clean up */
    free(srcBuffer);
}