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
typedef  int /*<<< orphan*/  testBlock_t ;

/* Variables and functions */
 int ALIGNMENTS ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  mc ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 scalar_t__ random () ; 

__attribute__((used)) static void
runTest(unsigned char *b1, unsigned char *b2)
{
	int	i, j, k, m;
	size_t	n;

	for (i = 0; i < ALIGNMENTS; ++i) {
		for (j = 0; j < ALIGNMENTS; ++j) {
			k = sizeof(testBlock_t) - (i > j ? i : j);
			for (m = 0; m < k; ++m) {
				for (n = 0; n < sizeof(testBlock_t); ++n) {
					b1[n] = (unsigned char)random();
					b2[n] = (unsigned char)random();
				}
				memcpy(b1 + i, b2 + j, m);
				MD5Update(mc, b1, sizeof(testBlock_t));
				MD5Update(mc, b2, sizeof(testBlock_t));
			}
		}
	}
}