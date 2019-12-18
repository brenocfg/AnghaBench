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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct open_file {int /*<<< orphan*/  f_fsdata; } ;
struct dirent {size_t d_namlen; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_fileno; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int CALLBACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readdir ; 

__attribute__((used)) static int
host_readdir(struct open_file *f, struct dirent *d)
{
	uint32_t fileno;
	uint8_t type;
	size_t namelen;
	int rc;

	rc = CALLBACK(readdir, f->f_fsdata, &fileno, &type, &namelen,
            d->d_name);
	if (rc)
		return (rc);

	d->d_fileno = fileno;
	d->d_type = type;
	d->d_namlen = namelen;

	return (0);
}