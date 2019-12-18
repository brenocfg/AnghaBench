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
struct aiocb {int dummy; } ;

/* Variables and functions */
 int copyin (struct aiocb*,struct aiocb*,int) ; 

__attribute__((used)) static int
aiocb_copyin(struct aiocb *ujob, struct aiocb *kjob)
{

	return (copyin(ujob, kjob, sizeof(struct aiocb)));
}