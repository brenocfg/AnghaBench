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
union drbd_state {scalar_t__ susp_fen; scalar_t__ susp_nod; scalar_t__ susp; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_susp(union drbd_state s)
{
        return s.susp || s.susp_nod || s.susp_fen;
}