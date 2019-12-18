__attribute__((used)) static const char *
decode_wait_status(int status)
{
	static char c[128];
	char b[32];
	int first;

	c[0] = '\0';
	first = 1;
	if (WIFCONTINUED(status)) {
		first = 0;
		strlcat(c, "CONT", sizeof(c));
	}
	if (WIFEXITED(status)) {
		if (first)
			first = 0;
		else
			strlcat(c, ",", sizeof(c));
		snprintf(b, sizeof(b), "EXIT(%d)", WEXITSTATUS(status));
		strlcat(c, b, sizeof(c));
	}
	if (WIFSIGNALED(status)) {
		if (first)
			first = 0;
		else
			strlcat(c, ",", sizeof(c));
		snprintf(b, sizeof(b), "SIG(%s)", strsignal(WTERMSIG(status)));
		strlcat(c, b, sizeof(c));
		if (WCOREDUMP(status))
			strlcat(c, ",CORE", sizeof(c));
	}
	if (WIFSTOPPED(status)) {
		if (first)
			first = 0;
		else
			strlcat(c, ",", sizeof(c));
		snprintf(b, sizeof(b), "SIG(%s)", strsignal(WSTOPSIG(status)));
		strlcat(c, b, sizeof(c));
	}
	return (c);
}