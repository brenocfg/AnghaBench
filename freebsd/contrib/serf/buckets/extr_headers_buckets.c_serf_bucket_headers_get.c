#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  allocator; TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_6__ {TYPE_3__* list; } ;
typedef  TYPE_2__ headers_context_t ;
struct TYPE_7__ {int value_size; char const* value; struct TYPE_7__* next; int /*<<< orphan*/  header; } ;
typedef  TYPE_3__ header_list_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int ALLOC_VALUE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* serf_bucket_mem_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serf_bucket_mem_free (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

const char *serf_bucket_headers_get(
    serf_bucket_t *headers_bucket,
    const char *header)
{
    headers_context_t *ctx = headers_bucket->data;
    header_list_t *found = ctx->list;
    const char *val = NULL;
    int value_size = 0;
    int val_alloc = 0;

    while (found) {
        if (strcasecmp(found->header, header) == 0) {
            if (val) {
                /* The header is already present.  RFC 2616, section 4.2
                   indicates that we should append the new value, separated by
                   a comma.  Reasoning: for headers whose values are known to
                   be comma-separated, that is clearly the correct behavior;
                   for others, the correct behavior is undefined anyway. */

                /* The "+1" is for the comma; the +1 in the alloc
                   call is for the terminating '\0' */
                apr_size_t new_size = found->value_size + value_size + 1;
                char *new_val = serf_bucket_mem_alloc(headers_bucket->allocator,
                                                      new_size + 1);
                memcpy(new_val, val, value_size);
                new_val[value_size] = ',';
                memcpy(new_val + value_size + 1, found->value,
                       found->value_size);
                new_val[new_size] = '\0';
                /* Copy the new value over the already existing value. */
                if (val_alloc)
                    serf_bucket_mem_free(headers_bucket->allocator, (void*)val);
                val_alloc |= ALLOC_VALUE;
                val = new_val;
                value_size = new_size;
            }
            else {
                val = found->value;
                value_size = found->value_size;
            }
        }
        found = found->next;
    }

    return val;
}