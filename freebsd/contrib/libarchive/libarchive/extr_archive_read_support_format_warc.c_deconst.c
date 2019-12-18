__attribute__((used)) static void*
deconst(const void *c)
{
	return (char *)0x1 + (((const char *)c) - (const char *)0x1);
}