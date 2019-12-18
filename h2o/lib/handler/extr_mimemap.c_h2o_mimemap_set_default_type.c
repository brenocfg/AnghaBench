#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  attr; } ;
struct TYPE_9__ {TYPE_1__ data; } ;
typedef  TYPE_2__ h2o_mimemap_type_t ;
typedef  int /*<<< orphan*/  h2o_mimemap_t ;
typedef  int /*<<< orphan*/  h2o_mime_attributes_t ;

/* Variables and functions */
 TYPE_2__* create_extension_type (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_iovec_init (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_addref_shared (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (TYPE_2__*) ; 
 TYPE_2__* h2o_mimemap_get_type_by_mimetype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_default_type (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void h2o_mimemap_set_default_type(h2o_mimemap_t *mimemap, const char *mime, h2o_mime_attributes_t *attr)
{
    h2o_mimemap_type_t *new_type;

    /* obtain or create new type */
    if ((new_type = h2o_mimemap_get_type_by_mimetype(mimemap, h2o_iovec_init(mime, strlen(mime)), 1)) != NULL &&
        (attr == NULL || memcmp(&new_type->data.attr, attr, sizeof(*attr)) == 0)) {
        h2o_mem_addref_shared(new_type);
    } else {
        new_type = create_extension_type(mime, attr);
    }

    set_default_type(mimemap, new_type);
    h2o_mem_release_shared(new_type);
}