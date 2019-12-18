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
typedef  TYPE_1__* epoch_t ;
typedef  int /*<<< orphan*/  epoch_record_t ;
struct TYPE_3__ {int /*<<< orphan*/  e_pcpu_record; } ;

/* Variables and functions */
 int /*<<< orphan*/  curcpu ; 
 int /*<<< orphan*/  zpcpu_get_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static epoch_record_t
epoch_currecord(epoch_t epoch)
{

	return (zpcpu_get_cpu(epoch->e_pcpu_record, curcpu));
}