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
typedef  int /*<<< orphan*/  h2o_mimemap_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_mimemap_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_mimemap_create () ; 
 int /*<<< orphan*/  h2o_mimemap_define_mimetype (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_mimemap_get_default_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_mimemap_get_type_by_extension (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_mimemap_get_type_by_mimetype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mimemap_remove_type (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  h2o_mimemap_set_default_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int is_mimetype (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_default_attributes ; 

__attribute__((used)) static void test_basic()
{
    h2o_mimemap_t *mimemap = h2o_mimemap_create(), *mimemap2;

    subtest("default-attributes", test_default_attributes);

    /* default and set default */
    ok(is_mimetype(h2o_mimemap_get_default_type(mimemap), "application/octet-stream"));
    {
        char buf[sizeof("text/plain")];
        strcpy(buf, "text/plain");
        h2o_mimemap_set_default_type(mimemap, buf, NULL);
        memset(buf, 0, sizeof(buf));
    }
    ok(is_mimetype(h2o_mimemap_get_default_type(mimemap), "text/plain"));

    /* set and overwrite */
    h2o_mimemap_define_mimetype(mimemap, "foo", "example/foo", NULL);
    ok(is_mimetype(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("foo"))), "example/foo"));
    ok(is_mimetype(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("FOO"))), "example/foo"));
    ok(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("foo"))) ==
       h2o_mimemap_get_type_by_mimetype(mimemap, h2o_iovec_init(H2O_STRLIT("example/foo")), 0));
    h2o_mimemap_define_mimetype(mimemap, "foo", "example/overwritten", NULL);
    ok(is_mimetype(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("foo"))), "example/overwritten"));
    ok(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("foo"))) ==
       h2o_mimemap_get_type_by_mimetype(mimemap, h2o_iovec_init(H2O_STRLIT("example/overwritten")), 0));
    ok(h2o_mimemap_get_type_by_mimetype(mimemap, h2o_iovec_init(H2O_STRLIT("example/foo")), 0) == NULL);

    /* clone and release */
    mimemap2 = h2o_mimemap_clone(mimemap);
    ok(is_mimetype(h2o_mimemap_get_default_type(mimemap2), "text/plain"));
    ok(is_mimetype(h2o_mimemap_get_type_by_extension(mimemap2, h2o_iovec_init(H2O_STRLIT("foo"))), "example/overwritten"));
    ok(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("foo"))) ==
       h2o_mimemap_get_type_by_mimetype(mimemap, h2o_iovec_init(H2O_STRLIT("example/overwritten")), 0));
    h2o_mem_release_shared(mimemap2);

    /* check original */
    ok(is_mimetype(h2o_mimemap_get_default_type(mimemap), "text/plain"));
    ok(is_mimetype(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("foo"))), "example/overwritten"));

    /* remove */
    h2o_mimemap_remove_type(mimemap, "foo");
    ok(is_mimetype(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("foo"))), "text/plain"));
    ok(h2o_mimemap_get_type_by_mimetype(mimemap, h2o_iovec_init(H2O_STRLIT("example/overwritten")), 0) == NULL);
    h2o_mimemap_remove_type(mimemap, "foo");
    ok(is_mimetype(h2o_mimemap_get_type_by_extension(mimemap, h2o_iovec_init(H2O_STRLIT("foo"))), "text/plain"));

    h2o_mem_release_shared(mimemap);
}