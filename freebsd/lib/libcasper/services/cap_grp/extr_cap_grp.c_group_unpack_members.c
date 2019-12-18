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
typedef  int /*<<< orphan*/  nvlname ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ _ALIGN (char*) ; 
 size_t _ALIGNBYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 char* dnvlist_get_string (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  nvlist_exists_number (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 
 int snprintf (char*,int,char*,unsigned int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
group_unpack_members(const nvlist_t *nvl, char ***fieldp, char **bufferp,
    size_t *bufsizep)
{
	const char *mem;
	char **outstrs, *str, nvlname[64];
	size_t nmem, datasize, strsize;
	unsigned int ii;
	int n;

	if (!nvlist_exists_number(nvl, "gr_nmem")) {
		datasize = _ALIGNBYTES + sizeof(char *);
		if (datasize >= *bufsizep)
			return (ERANGE);
		outstrs = (char **)_ALIGN(*bufferp);
		outstrs[0] = NULL;
		*fieldp = outstrs;
		*bufferp += datasize;
		*bufsizep -= datasize;
		return (0);
	}

	nmem = (size_t)nvlist_get_number(nvl, "gr_nmem");
	datasize = _ALIGNBYTES + sizeof(char *) * (nmem + 1);
	for (ii = 0; ii < nmem; ii++) {
		n = snprintf(nvlname, sizeof(nvlname), "gr_mem[%u]", ii);
		assert(n > 0 && n < (int)sizeof(nvlname));
		mem = dnvlist_get_string(nvl, nvlname, NULL);
		if (mem == NULL)
			return (EINVAL);
		datasize += strlen(mem) + 1;
	}

	if (datasize >= *bufsizep)
		return (ERANGE);

	outstrs = (char **)_ALIGN(*bufferp);
	str = (char *)outstrs + sizeof(char *) * (nmem + 1);
	for (ii = 0; ii < nmem; ii++) {
		n = snprintf(nvlname, sizeof(nvlname), "gr_mem[%u]", ii);
		assert(n > 0 && n < (int)sizeof(nvlname));
		mem = nvlist_get_string(nvl, nvlname);
		strsize = strlen(mem) + 1;
		memcpy(str, mem, strsize);
		outstrs[ii] = str;
		str += strsize;
	}
	assert(ii == nmem);
	outstrs[ii] = NULL;

	*fieldp = outstrs;
	*bufferp += datasize;
	*bufsizep -= datasize;

	return (0);
}