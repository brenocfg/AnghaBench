__attribute__((used)) static const char *
get_ucpname(unsigned int ptype, unsigned int pvalue)
{
#ifdef SUPPORT_UCP
int i;
for (i = PRIV(utt_size) - 1; i >= 0; i--)
  {
  if (ptype == PRIV(utt)[i].type && pvalue == PRIV(utt)[i].value) break;
  }
return (i >= 0)? PRIV(utt_names) + PRIV(utt)[i].name_offset : "??";
#else
/* It gets harder and harder to shut off unwanted compiler warnings. */
ptype = ptype * pvalue;
return (ptype == pvalue)? "??" : "??";
#endif
}