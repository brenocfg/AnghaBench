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
typedef  int /*<<< orphan*/  token_t ;
typedef  int /*<<< orphan*/  au_event_t ;
typedef  int /*<<< orphan*/  au_emod_t ;

/* Variables and functions */
 int /*<<< orphan*/ * au_to_header32 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

token_t *
au_to_header(int rec_size, au_event_t e_type, au_emod_t e_mod)
{

	return (au_to_header32(rec_size, e_type, e_mod));
}