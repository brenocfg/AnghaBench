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
struct file_data {char const* filename; char const* mode; int keep_open; int /*<<< orphan*/ * fd; } ;
typedef  int /*<<< orphan*/  krb5_log_facility ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  krb5_addlog_func (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file_data*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_file ; 
 struct file_data* malloc (int) ; 

__attribute__((used)) static krb5_error_code
open_file(krb5_context context, krb5_log_facility *fac, int min, int max,
	  const char *filename, const char *mode, FILE *f, int keep_open)
{
    struct file_data *fd = malloc(sizeof(*fd));
    if(fd == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    fd->filename = filename;
    fd->mode = mode;
    fd->fd = f;
    fd->keep_open = keep_open;

    return krb5_addlog_func(context, fac, min, max, log_file, close_file, fd);
}