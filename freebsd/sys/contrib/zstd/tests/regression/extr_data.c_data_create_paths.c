#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * path; } ;
struct TYPE_7__ {int /*<<< orphan*/ * path; } ;
struct TYPE_8__ {TYPE_1__ dict; TYPE_2__ data; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ data_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cat2 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * cat3 (char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ data_has_dict (TYPE_3__* const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int data_create_paths(data_t* const* data, char const* dir) {
    size_t const dirlen = strlen(dir);
    assert(data != NULL);
    for (; *data != NULL; ++data) {
        data_t* const datum = *data;
        datum->data.path = cat3(dir, "/", datum->name);
        if (datum->data.path == NULL)
            return ENOMEM;
        if (data_has_dict(datum)) {
            datum->dict.path = cat2(datum->data.path, ".dict");
            if (datum->dict.path == NULL)
                return ENOMEM;
        }
    }
    return 0;
}