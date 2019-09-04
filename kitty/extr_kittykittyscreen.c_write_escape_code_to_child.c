#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ eight_bit_controls; } ;
struct TYPE_6__ {scalar_t__ test_child; scalar_t__ window_id; TYPE_1__ modes; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
#define  APC 132 
#define  CSI 131 
#define  DCS 130 
#define  OSC 129 
#define  PM 128 
 scalar_t__ Py_None ; 
 int /*<<< orphan*/  fatal (char*,unsigned char) ; 
 int /*<<< orphan*/  schedule_write_to_child (scalar_t__,int,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  write_to_test_child (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 

void
write_escape_code_to_child(Screen *self, unsigned char which, const char *data) {
    const char *prefix, *suffix = self->modes.eight_bit_controls ? "\x9c" : "\033\\";
    switch(which) {
        case DCS:
            prefix = self->modes.eight_bit_controls ? "\x90" : "\033P";
            break;
        case CSI:
            prefix = self->modes.eight_bit_controls ? "\x9b" : "\033["; suffix = "";
            break;
        case OSC:
            prefix = self->modes.eight_bit_controls ? "\x9d" : "\033]";
            break;
        case PM:
            prefix = self->modes.eight_bit_controls ? "\x9e" : "\033^";
            break;
        case APC:
            prefix = self->modes.eight_bit_controls ? "\x9f" : "\033_";
            break;
        default:
            fatal("Unknown escape code to write: %u", which);
    }
    if (self->window_id) {
        if (suffix[0]) {
            schedule_write_to_child(self->window_id, 3, prefix, strlen(prefix), data, strlen(data), suffix, strlen(suffix));
        } else {
            schedule_write_to_child(self->window_id, 2, prefix, strlen(prefix), data, strlen(data));
        }
    }
    if (self->test_child != Py_None) {
        write_to_test_child(self, prefix, strlen(prefix));
        write_to_test_child(self, data, strlen(data));
        if (suffix[0]) write_to_test_child(self, suffix, strlen(suffix));
    }
}