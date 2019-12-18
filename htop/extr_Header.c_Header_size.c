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
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_3__ {int /*<<< orphan*/ ** columns; } ;
typedef  TYPE_1__ Header ;

/* Variables and functions */
 int Vector_size (int /*<<< orphan*/ *) ; 

int Header_size(Header* this, int column) {
   Vector* meters = this->columns[column];
   return Vector_size(meters);
}