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
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MOVEDIR_DOWN ; 
 int /*<<< orphan*/  MOVEDIR_UP ; 
 int /*<<< orphan*/  VEC_DOWN ; 
 int /*<<< orphan*/  VEC_UP ; 
 scalar_t__ VectorCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotSetMovedir(vec3_t angles, vec3_t movedir) {
	if (VectorCompare(angles, VEC_UP)) {
		VectorCopy(MOVEDIR_UP, movedir);
	}
	else if (VectorCompare(angles, VEC_DOWN)) {
		VectorCopy(MOVEDIR_DOWN, movedir);
	}
	else {
		AngleVectors(angles, movedir, NULL, NULL);
	}
}