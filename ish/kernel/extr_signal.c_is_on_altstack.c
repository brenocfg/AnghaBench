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
struct sighand {scalar_t__ altstack; scalar_t__ altstack_size; } ;
typedef  scalar_t__ dword_t ;

/* Variables and functions */

__attribute__((used)) static bool is_on_altstack(dword_t sp, struct sighand *sighand) {
    return sp > sighand->altstack && sp <= sighand->altstack + sighand->altstack_size;
}