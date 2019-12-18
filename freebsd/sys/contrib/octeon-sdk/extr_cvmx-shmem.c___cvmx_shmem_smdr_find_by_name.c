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
struct cvmx_shmem_dscptr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_shmem_smdr_match_name ; 
 struct cvmx_shmem_dscptr* __smdr_iterator (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct cvmx_shmem_dscptr *__cvmx_shmem_smdr_find_by_name(char *name)
{
    return __smdr_iterator( __cvmx_shmem_smdr_match_name, name);
}