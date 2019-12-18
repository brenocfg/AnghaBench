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
typedef  int /*<<< orphan*/  fn ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  free_environment (char**) ; 
 int /*<<< orphan*/  make_file (char*,int) ; 
 int read_environment (char*,char***) ; 
 int /*<<< orphan*/  s1 ; 
 int /*<<< orphan*/  s2 ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 
 int /*<<< orphan*/  write_file (char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
    char **env = NULL;
    int count = 0;
    char fn[MAXPATHLEN];
    int error = 0;

    make_file(fn, sizeof(fn));

    write_file(fn, s1);
    count = read_environment(fn, &env);
    if(count != 3) {
	warnx("test 1: variable count %d != 3", count);
	error++;
    }

    write_file(fn, s2);
    count = read_environment(fn, &env);
    if(count != 1) {
	warnx("test 2: variable count %d != 1", count);
	error++;
    }

    unlink(fn);
    count = read_environment(fn, &env);
    if(count != 0) {
	warnx("test 3: variable count %d != 0", count);
	error++;
    }
    for(count = 0; env && env[count]; count++);
    if(count != 3) {
	warnx("total variable count %d != 3", count);
	error++;
    }
    free_environment(env);


    return error;
}