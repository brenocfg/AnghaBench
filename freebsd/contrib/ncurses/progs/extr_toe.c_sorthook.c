#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int db_index; void* description; void* term_name; int /*<<< orphan*/  checksum; } ;
typedef  int /*<<< orphan*/  TERMTYPE ;
typedef  TYPE_1__ TERMDATA ;

/* Variables and functions */
 int /*<<< orphan*/  checksum_of (int /*<<< orphan*/ *) ; 
 TYPE_1__* new_termdata () ; 
 void* strmalloc (char const*) ; 
 char const* term_description (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sorthook(int db_index, int db_limit, const char *term_name, TERMTYPE *tp)
{
    TERMDATA *data = new_termdata();

    data->db_index = db_index;
    data->checksum = ((db_limit > 1) ? checksum_of(tp) : 0);
    data->term_name = strmalloc(term_name);
    data->description = strmalloc(term_description(tp));
}