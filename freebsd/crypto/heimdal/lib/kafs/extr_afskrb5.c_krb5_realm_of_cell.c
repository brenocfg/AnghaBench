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
struct kafs_data {char* name; int /*<<< orphan*/  free_error; int /*<<< orphan*/  get_error; int /*<<< orphan*/  get_realm; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  _kafs_realm_of_cell (struct kafs_data*,char const*,char**) ; 
 int /*<<< orphan*/  free_error ; 
 int /*<<< orphan*/  get_error ; 
 int /*<<< orphan*/  get_realm ; 

krb5_error_code
krb5_realm_of_cell(const char *cell, char **realm)
{
    struct kafs_data kd;

    kd.name = "krb5";
    kd.get_realm = get_realm;
    kd.get_error = get_error;
    kd.free_error = free_error;
    return _kafs_realm_of_cell(&kd, cell, realm);
}