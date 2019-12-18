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
struct val_env {size_t* nsec3_keysize; size_t* nsec3_maxiter; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
fill_nsec3_iter(struct val_env* ve, char* s, int c)
{
	char* e;
	int i;
	free(ve->nsec3_keysize);
	free(ve->nsec3_maxiter);
	ve->nsec3_keysize = (size_t*)calloc(sizeof(size_t), (size_t)c);
	ve->nsec3_maxiter = (size_t*)calloc(sizeof(size_t), (size_t)c);
	if(!ve->nsec3_keysize || !ve->nsec3_maxiter) {
		log_err("out of memory");
		return 0;
	}
	for(i=0; i<c; i++) {
		ve->nsec3_keysize[i] = (size_t)strtol(s, &e, 10);
		if(s == e) {
			log_err("cannot parse: %s", s);
			return 0;
		}
		s = e;
		ve->nsec3_maxiter[i] = (size_t)strtol(s, &e, 10);
		if(s == e) {
			log_err("cannot parse: %s", s);
			return 0;
		}
		s = e;
		if(i>0 && ve->nsec3_keysize[i-1] >= ve->nsec3_keysize[i]) {
			log_err("nsec3 key iterations not ascending: %d %d",
				(int)ve->nsec3_keysize[i-1], 
				(int)ve->nsec3_keysize[i]);
			return 0;
		}
		verbose(VERB_ALGO, "validator nsec3cfg keysz %d mxiter %d",
			(int)ve->nsec3_keysize[i], (int)ve->nsec3_maxiter[i]);
	}
	return 1;
}