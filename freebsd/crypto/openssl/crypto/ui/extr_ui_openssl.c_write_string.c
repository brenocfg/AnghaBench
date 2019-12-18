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
typedef  int /*<<< orphan*/  UI_STRING ;
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
#define  UIT_BOOLEAN 133 
#define  UIT_ERROR 132 
#define  UIT_INFO 131 
#define  UIT_NONE 130 
#define  UIT_PROMPT 129 
#define  UIT_VERIFY 128 
 int /*<<< orphan*/  UI_get0_output_string (int /*<<< orphan*/ *) ; 
 int UI_get_string_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_out ; 

__attribute__((used)) static int write_string(UI *ui, UI_STRING *uis)
{
    switch (UI_get_string_type(uis)) {
    case UIT_ERROR:
    case UIT_INFO:
        fputs(UI_get0_output_string(uis), tty_out);
        fflush(tty_out);
        break;
    case UIT_NONE:
    case UIT_PROMPT:
    case UIT_VERIFY:
    case UIT_BOOLEAN:
        break;
    }
    return 1;
}