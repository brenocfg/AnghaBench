void *edac_align_ptr(void **p, unsigned int size, int n_elems)
{
	unsigned int align, r;
	void *ptr = *p;

	*p += size * n_elems;

	/*
	 * 'p' can possibly be an unaligned item X such that sizeof(X) is
	 * 'size'.  Adjust 'p' so that its alignment is at least as
	 * stringent as what the compiler would provide for X and return
	 * the aligned result.
	 * Here we assume that the alignment of a "long long" is the most
	 * stringent alignment that the compiler will ever provide by default.
	 * As far as I know, this is a reasonable assumption.
	 */
	if (size > sizeof(long))
		align = sizeof(long long);
	else if (size > sizeof(int))
		align = sizeof(long);
	else if (size > sizeof(short))
		align = sizeof(int);
	else if (size > sizeof(char))
		align = sizeof(short);
	else
		return (char *)ptr;

	r = (unsigned long)p % align;

	if (r == 0)
		return (char *)ptr;

	*p += align - r;

	return (void *)(((unsigned long)ptr) + align - r);
}