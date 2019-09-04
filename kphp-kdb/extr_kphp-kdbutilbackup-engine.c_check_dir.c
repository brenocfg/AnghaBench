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
struct stat {int st_dev; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 scalar_t__ MAX_DIRNAME_LEN ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ mkdir (char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int check_dir (char *dirname, struct stat *buf, int create) {
  if (stat (dirname, buf) < 0) {
    if (errno != ENOENT || !create) {
      return -1;
    }
    if (mkdir (dirname, 0750) < 0) {
      return -1;
    }
    if (stat (dirname, buf) < 0) {
      return -1;
    }
  }
  if (!S_ISDIR (buf->st_mode) || strlen (dirname) > MAX_DIRNAME_LEN) {
    errno = ENOTDIR;
    return -1;
  }
  return buf->st_dev;
}