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
typedef  int /*<<< orphan*/  hx509_peer_info ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_8__ {int num_strings; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ getarg_strings ;
struct TYPE_9__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_2__ AlgorithmIdentifier ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  free_AlgorithmIdentifier (TYPE_2__*) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int hx509_peer_info_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_peer_info_set_cms_algs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  parse_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
peer_strings(hx509_context contextp,
	     hx509_peer_info *peer,
	     const getarg_strings *s)
{
    AlgorithmIdentifier *val;
    int ret, i;

    ret = hx509_peer_info_alloc(contextp, peer);
    if (ret)
	hx509_err(contextp, 1, ret, "hx509_peer_info_alloc");

    val = calloc(s->num_strings, sizeof(*val));
    if (val == NULL)
	err(1, "malloc");

    for (i = 0; i < s->num_strings; i++)
	parse_oid(s->strings[i], NULL, &val[i].algorithm);

    ret = hx509_peer_info_set_cms_algs(contextp, *peer, val, s->num_strings);
    if (ret)
	hx509_err(contextp, 1, ret, "hx509_peer_info_set_cms_algs");

    for (i = 0; i < s->num_strings; i++)
	free_AlgorithmIdentifier(&val[i]);
    free(val);
}