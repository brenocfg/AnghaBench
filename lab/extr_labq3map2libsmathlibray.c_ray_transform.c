#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  direction; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ ray_t ;
typedef  int /*<<< orphan*/  m4x4_t ;

/* Variables and functions */
 int /*<<< orphan*/  m4x4_transform_normal (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m4x4_transform_point (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

void ray_transform( ray_t *ray, const m4x4_t matrix ){
	m4x4_transform_point( matrix, ray->origin );
	m4x4_transform_normal( matrix, ray->direction );
}