long
fuword(volatile const void *addr)
{
	long val;
	int rv;

	rv = fueword(addr, &val);
	return (rv == -1 ? -1 : val);
}