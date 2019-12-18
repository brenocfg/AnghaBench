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
typedef  int /*<<< orphan*/  uint32_t ;
struct example {size_t out_len; int /*<<< orphan*/  out; int /*<<< orphan*/  in_len; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIND_PROFILE_NAME ; 
 int _wind_stringprep_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
try(const struct example *c)
{
    int ret;
    size_t out_len = c->out_len;
    uint32_t *tmp = malloc(out_len * sizeof(uint32_t));
    if (tmp == NULL && out_len != 0)
	err(1, "malloc");
    ret = _wind_stringprep_map(c->in, c->in_len, tmp, &out_len, WIND_PROFILE_NAME);
    if (ret) {
	printf("wind_stringprep_map failed\n");
	return 1;
    }
    if (out_len != c->out_len) {
	printf("wrong out len\n");
	free(tmp);
	return 1;
    }
    if (memcmp(c->out, tmp, out_len * sizeof(uint32_t)) != 0) {
	printf("wrong out data\n");
	free(tmp);
	return 1;
    }
    free(tmp);
    return 0;
}