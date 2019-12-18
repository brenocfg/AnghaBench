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
typedef  int /*<<< orphan*/  u32 ;
struct nbpf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBPF_DSTAT_ER ; 
 int /*<<< orphan*/  nbpf_read (struct nbpf_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nbpf_error_get(struct nbpf_device *nbpf)
{
	return nbpf_read(nbpf, NBPF_DSTAT_ER);
}