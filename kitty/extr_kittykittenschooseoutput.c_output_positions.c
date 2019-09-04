#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  size_t len_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {char* output; int /*<<< orphan*/  output_pos; } ;
typedef  TYPE_1__ GlobalData ;

/* Variables and functions */
 scalar_t__ ensure_space (TYPE_1__*,int) ; 
 int swprintf (char*,int,char*,size_t) ; 

__attribute__((used)) static void
output_positions(GlobalData *global, len_t *positions, len_t num) {
    wchar_t buf[128];
    for (len_t i = 0; i < num; i++) {
        int num = swprintf(buf, sizeof(buf)/sizeof(buf[0]), L"%u", positions[i]);
        if (num > 0 && ensure_space(global, num + 1)) {
            for (int i = 0; i < num; i++) global->output[global->output_pos++] = buf[i];
            global->output[global->output_pos++] = (i == num - 1) ? ',' : ':';
        }
    }
}