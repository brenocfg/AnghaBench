__attribute__((used)) static __inline void
ofwo_printprop(const char *prop, const char* buf, int buflen)
{

	printf("%s: %.*s\n", prop, buflen, buf);
}