int
set_rdomain(int fd, const char *name)
{
#if defined(HAVE_SYS_SET_RDOMAIN)
	return sys_set_rdomain(fd, name);
#elif defined(__OpenBSD__)
	int rtable;
	const char *errstr;

	if (name == NULL)
		return 0; /* default table */

	rtable = (int)strtonum(name, 0, 255, &errstr);
	if (errstr != NULL) {
		/* Shouldn't happen */
		error("Invalid routing domain \"%s\": %s", name, errstr);
		return -1;
	}
	if (setsockopt(fd, SOL_SOCKET, SO_RTABLE,
	    &rtable, sizeof(rtable)) == -1) {
		error("Failed to set routing domain %d on fd %d: %s",
		    rtable, fd, strerror(errno));
		return -1;
	}
	return 0;
#else /* defined(__OpenBSD__) */
	error("Setting routing domain is not supported on this platform");
	return -1;
#endif
}