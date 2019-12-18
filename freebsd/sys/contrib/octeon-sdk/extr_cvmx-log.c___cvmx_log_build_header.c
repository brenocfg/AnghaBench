#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  cvmx_log_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  cycle; scalar_t__ size; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_log_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_get_cycle () ; 

__attribute__((used)) static inline uint64_t __cvmx_log_build_header(cvmx_log_type_t type, uint64_t size)
{
    cvmx_log_header_t header;
    header.u64 = 0;
    header.s.type = type;
    header.s.size = size;
    header.s.cycle = cvmx_get_cycle();
    return header.u64;
}