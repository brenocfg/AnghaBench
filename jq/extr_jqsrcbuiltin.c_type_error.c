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
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_dump_string_trunc (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_kind_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static jv type_error(jv bad, const char* msg) {
  char errbuf[15];
  jv err = jv_invalid_with_msg(jv_string_fmt("%s (%s) %s",
                                             jv_kind_name(jv_get_kind(bad)),
                                             jv_dump_string_trunc(jv_copy(bad), errbuf, sizeof(errbuf)),
                                             msg));
  jv_free(bad);
  return err;
}