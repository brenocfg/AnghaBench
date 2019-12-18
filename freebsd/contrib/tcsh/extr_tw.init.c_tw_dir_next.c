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
struct dirent {int /*<<< orphan*/  d_name; } ;
struct Strbuf {int dummy; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str2short (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tw_dir_next(struct Strbuf *res, DIR *dfd)
{
    struct dirent *dirp;

    if (dfd == NULL)
	return 0;

    if ((dirp = readdir(dfd)) != NULL) {
	Strbuf_append(res, str2short(dirp->d_name));
	return 1;
    }
    return 0;
}