#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ index; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ data_prot ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 TYPE_1__ out_buffer ; 
 scalar_t__ prot_clear ; 
 int /*<<< orphan*/  sec_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
sec_fflush(FILE *F)
{
    if(data_prot != prot_clear) {
	if(out_buffer.index > 0){
	    sec_write(fileno(F), out_buffer.data, out_buffer.index);
	    out_buffer.index = 0;
	}
	sec_send(fileno(F), NULL, 0);
    }
    fflush(F);
    return 0;
}