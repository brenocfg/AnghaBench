#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  h2o_token_t ;
struct TYPE_9__ {TYPE_2__* entries; } ;
struct TYPE_8__ {TYPE_4__ headers; } ;
typedef  TYPE_3__ h2o_res_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {TYPE_1__ value; } ;

/* Variables and functions */
 int h2o_find_header (TYPE_4__*,int /*<<< orphan*/  const*,int) ; 
 int h2o_lcstris (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int check_header(h2o_res_t *res, const h2o_token_t *header_name, const char *expected)
{
    ssize_t index = h2o_find_header(&res->headers, header_name, -1);
    if (index == -1)
        return 0;
    return h2o_lcstris(res->headers.entries[index].value.base, res->headers.entries[index].value.len, expected, strlen(expected));
}