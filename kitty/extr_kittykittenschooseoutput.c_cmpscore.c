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

/* Variables and functions */
 double FIELD (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idx ; 
 int /*<<< orphan*/  score ; 

__attribute__((used)) static int
cmpscore(const void *a, const void *b) {
    double sa = FIELD(a, score), sb = FIELD(b, score);
    // Sort descending
    return (sa > sb) ? -1 : ((sa == sb) ? ((int)FIELD(a, idx) - (int)FIELD(b, idx)) : 1);
}