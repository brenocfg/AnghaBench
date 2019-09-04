#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* base; size_t len; } ;
struct TYPE_8__ {int /*<<< orphan*/  attr; TYPE_1__ mimetype; } ;
struct TYPE_9__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ h2o_mimemap_type_t ;
typedef  int /*<<< orphan*/  h2o_mime_attributes_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MIMEMAP_TYPE_MIMETYPE ; 
 TYPE_3__* h2o_mem_alloc_shared (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mimemap_get_default_attributes (char const*,int /*<<< orphan*/ *) ; 
 char h2o_tolower (char const) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static h2o_mimemap_type_t *create_extension_type(const char *mime, h2o_mime_attributes_t *attr)
{
    h2o_mimemap_type_t *type = h2o_mem_alloc_shared(NULL, sizeof(*type) + strlen(mime) + 1, NULL);
    size_t i;

    memset(type, 0, sizeof(*type));

    type->type = H2O_MIMEMAP_TYPE_MIMETYPE;

    /* normalize-copy type->data.mimetype */
    type->data.mimetype.base = (char *)type + sizeof(*type);
    for (i = 0; mime[i] != '\0' && mime[i] != ';'; ++i)
        type->data.mimetype.base[i] = h2o_tolower(mime[i]);
    for (; mime[i] != '\0'; ++i)
        type->data.mimetype.base[i] = mime[i];
    type->data.mimetype.base[i] = '\0';
    type->data.mimetype.len = i;

    if (attr != NULL) {
        type->data.attr = *attr;
    } else {
        h2o_mimemap_get_default_attributes(mime, &type->data.attr);
    }

    return type;
}